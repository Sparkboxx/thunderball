"""
  esc.py - Python Module for Controlling an ESC
  Created by Michalis Agathos and Wilco van Duinkerken, november 2013
  Released into the public domain.
"""

import time
import Adafruit_BBIO.PWM as pwm
import Adafruit_BBIO.GPIO as gpio

PWMpins = {'P9_14', 'P9_16', 'P9_21', 'P9_22', 'P9_28', 'P9_29', 'P9_31', 'P9_42', 'P8_13', 'P8_19', 'P8_34', 'P8_36', 'P8_45', 'P8_46'}

HIGH = gpio.HIGH
LOW = gpio.LOW
IN = gpio.IN
OUT = gpio.OUT

escList = []

def power_up_all(eList):
  for e in eList:
    e.power_up()

def power_down_all(eList):
  for e in eList:
    e.power_down()

def attach_all(eList):
  for e in eList:
    e.attach()

def arm_all(eList):
  for e in eList:
    e.arm()

def disarm_all(eList):
  for e in eList:
    e.disarm()

def arm_all(eList):
  for e in eList:
    e.arm()

def calibrate_all(eList):
  for e in eList:
    e.calibrate()

def get_speeds(eList):
  speeds = []
  for e in eList:
    speeds.append(e._speed)
  print repr(speeds)


# More: set_speeds(speeds): if speed.len() is 1: set common speed, else if speed.len() is list.len() set speeds individually. 


def is_sane(lista, esc):
  """Sanity checks _signal_pin, _power_pin and name"""
  clashes = 0
  if esc._signal_pin not in PWMpins:
    print "Pin " + esc._signal_pin + " is not a valid PWM pin."
    clashes+=1
  if esc._power_pin in PWMpins:
    print "Pin " + esc._power_pin + " should be used as a PWM pin."
    clashes+=1
  for e in lista:
    if e._signal_pin is esc._signal_pin:
      print "PWM pin " + esc._signal_pin + " is already taken by " + e._name
      clashes+=1
    if e._power_pin is esc._power_pin:
      print "GPIO pin " + e._power_pin + " is already taken by " + e._name
      clashes+=1
    if e._name is esc._name:
      print "This name is already taken!"
      clashes+=1
  return not clashes



class ESC:
  """A class for Electronic Speed Controllers"""
  pin_setup = gpio.setup
  output = gpio.output
  start = pwm.start
  stop = pwm.stop
  cleanup = pwm.cleanup
  set_duty = pwm.set_duty_cycle
  set_update_freq = pwm.set_frequency

  specs = {'Icont':20, 'Iburst':30, 'freqs':[8000.0,16000.0], 'batts':['LiPo2', 'LiPo3', 'LiPo4', 'Ni5', 'Ni6', 'Ni7', 'Ni8', 'Ni9', 'Ni10', 'Ni11', 'Ni12'], 'reverse':True, 'SBEC':True, 'm':0.018}

  def __init__(self, signal_pin, power_pin, name,  min=800, max=2000, prog_mode=False):
      """ Creates the ESC using the following arguments:
      'signal_pin' (string) name of the PWM pin that outputs the signal
      'power_pin' (string) name of the GPIO pin that controls the power
      'name' (string) identifier for the ESC
      'min' (float) the minimum duty cycle width in microseconds (def 800)
      'max' (float) the maximum duty cycle width in microseconds (def 2000)
      'prog_mode' (boolean) true if user wants to go into programming mode (not ready yet)
      Since the period is 1/updatefreq, duty can be translated from microsec to % by *100*updatefreq/1000000
      """
      self._name = name
      self._opfreq = 8000.0 
      self._updatefreq = 100.0
      self._reverse = False
      self._attached = False
      self._armed = False
      self._powered = False
      self._speed = 0.0
      self._signal_pin = signal_pin
      self._power_pin = power_pin
      self._duty_us_min = min
      self._duty_us_max = max
      self._duty_cycle_min = self.us_to_pc(min)
      self._duty_cycle_max = self.us_to_pc(max)
      self.reset_span()
      self._prog_mode = prog_mode
      if not is_sane(escList, self):
        self._signal_pin = None
        self._power_pin = None
        self._name = None
      else:
        escList.append(self)

      #Sanity check? 
      #if signal_pin not in pwmPins:
      #  print "Selected signal pin does not support PWM"

  def attach(self):
      """Setup pins and arm."""
      self.pin_setup(self._power_pin, OUT)
      self.arm()
      print "Initialized ESC " + self._name + " using pin " + self._signal_pin + " to control signal and " + self._power_pin + " to control power."
      self._attached = True


  def reset_span(self):
      """Recalculates the width of duty range in microseconds. Should be used on init and 
      every time one of the duty_us_min and duty_us_max values changes"""
      self._span = self._duty_us_max - self._duty_us_min

  def calibrate(self, program=None):
      """Go through the throttle calibration procedure. Teaching the
      esc the min and max values of the throttle.
      Turn off the power, and then back on, while sending a full-throttle
      signal to the ESC through the PWM pin.
      Then wait for 2 sec and send a zero-throttle signal.
      If the 'prog_mode' flag is up, cycle through programming functions
      and interrupt on return key pressed."""
      if not self._attached:
        print "Attach before calibrating!"
        return
      if program is None:
        program = self._prog_mode
      print "Calibrating ESC " + self._name + "..."
      self.disarm()
      self.power_down()
      time.sleep(0.2)
      print "Setting full throttle..."
      self.arm()
      self.set_speed(1.0)
      print "Powering up..."
      self.power_up()
      time.sleep(2.0)
      if program:
          dummy = raw_input("Press return to choose function when cycle reaches its sound pattern.")
          
      print "Pulling throttle back to idle..."
      self.set_speed(0.0)
      print "Done calibrating ESC " + self._name + "!"
      

  def arm(self):
      """ Turn on the Engine at it's lowest speed"""
      if self._armed:
          return
      else:
          print "Arming ESC " + self._name + "..."
          self.start(self._signal_pin, self.us_to_pc(self._duty_us_min), self._updatefreq)
          self._armed = True


  def disarm(self):
      if not self._armed:
          return
      else:
          print "Disarming ESC " + self._name + "..."
          self.stop(self._signal_pin)
          self.cleanup()
          self._armed = False

  def us_to_pc(self, duty):
    return duty*self._updatefreq/10000.

  def normalize(self, duty_value):
      """Map duty range from microseconds to [0,1]"""
      return (duty_value - self._duty_us_min)/self._span

  def map(self, speed):
      """Inverse of normalize"""
      return speed*self._span + self._duty_us_min

  def increase(self, frac):
    """ Increase speed by a percentage expressed as a float > 0
    If a value is given outside of this range the function
    processes the max/min value instead."""
    if ( frac < 0 ):
        print "Relative shift must be >= 0!\n"
        return
    speed = min(self._speed*(1+frac), 1)
    self.set_speed(speed)

  def decrease(self, frac):
    """Decrease speed by a percentage of the current speed
    expressed as a float in [0,1]
    If a value is given outside of this range the function
    processes the max/min value instead."""
    if ( frac > 1 ):
        print "Relative shift must be < 1!\n"
        return
    speed = max(self._speed*(1-frac), 0)
    self.set_speed(speed)

  def shift_frac(self, frac):
    """ change speed by a percentage of the current speed.
    Expressed as a float >= -1
    If a value is given outside of this range the function
    processes the max/min value instead."""
    if ( frac < -1 ):
        print "Relative shift must be > -1!\n"
        return
    speed = max(0, min(self._speed*(1+frac), 1))
    self.set_speed(speed)
    

  def set_speed(self, speed=None):
    """ Set the speed as a fraction of the total capacity, 
    expressed as a float in [0,1].
    Examples:
      set_speed(0.10) puts the engine at 10% of maximum power
      set_speed(0.80) puts the engine at 80% of maximum power"""
    if speed is None:
      speed = self._speed
    self.set_duty(self._signal_pin, self.us_to_pc(self.map(speed)))
    self._speed = speed
    

  def set_abs_speed(self, duty=None):
    """Set the speed of the motor as an absolute value in microseconds within the
    ESC range. If a value outside of the min-max range is given
    the value is processed as being the max or min value possible."""
    if duty is None:
      duty = self.map(self.speed)
    self.set_duty(self.us_to_pc(duty))
    self._speed = self.normalize(duty)

  def power_up(self):
    """ Turn on external power to the ESC"""
    if not self._attached:
      print "Attach before powering up!"
      return
    self.output(self._power_pin, HIGH)
    self._powered = True
    print "ESC " + self._name + " powered up!"

  def power_down(self):
    if not self._attached:
      print "Attach before powering down!"
      return
    """ Turn off external power to the ESC"""
    self.output(self._power_pin, LOW)
    self._powered = False
    print "ESC " + self._name + " powered down!"

