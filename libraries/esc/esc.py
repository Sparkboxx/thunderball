"""
  esc.py - Python Module for Controlling an ESC
  Created by Michalis Agathos and Wilco van Duinkerken, november 2013
  Released into the public domain.
"""

import Adafruit_BBIO.PWM as pwm
import Adafruit_BBIO.GPIO as gpio


HIGH = gpio.HIGH
LOW = gpio.LOW
IN = gpio.IN
OUT = gpio.OUT

class ESC:
  """A class for Electronic Speed Controllers"""
  pin_setup = gpio.setup
  output = gpio.output
  start = pwm.start
  stop = pwm.stop
  cleanup = pwm.cleanup
  set_duty = pwm.set_duty_cycle
  set_update_freq = pwm.set_frequency

  specs = {Icont:20, Iburst:30, freqs:[8000.0,16000.0], batts:[LiPo2, LiPo3, LiPo4, Ni5, Ni6, Ni7, Ni8, Ni9, Ni10, Ni11, Ni12], reverse:True, SBEC:True, m:0.018}

  def __init__(self, signal_pin, power_pin, name,  min=800, max=2000, prog_mode=False):
      """ Creates the ESC using the following arguments:
      'signal_pin' (string) name of the PWM pin that outputs the signal
      'power_pin' (string) name of the GPIO pin that controls the power
      'min' (float) the minimum duty cycle width in microseconds (def 800)
      'max' (float) the maximum duty cycle width in microseconds (def 2000)
      'prog_mode' (boolean) true if user wants to go into programming mode (not ready yet)
      """
      self._name = name
      self._opfreq = 8000.0 
      self._updatefreq = 100.0
      self._reverse = False
      self._armed = False
      self._powered = False
      self._speed = 0.0
      self._power_pin = power_pin
      self._duty_min = min
      self._duty_max = max
      self.reset_span()
      self._prog_mode = prog_mode

      #Sanity check? 
      #if signal_pin not in pwmPins:
      #  print "Selected signal pin does not support PWM"

  def attach(self):
      """Setup pins and arm."""
      self.pin_setup(self._power_pin, OUT)
      self.arm()
      print "Initialized ESC " + self._name + " using pin " + signal_pin + " to control signal and " + power_pin + "to control power."


  def reset_span(self):
      """Recalculates the width of duty range. Should be used on init and 
      every time one of the duty_min and duty_max values changes"""
      self._span = self._duty_max - self._duty_min

  def calibrate(self, program=prog_mode):
      """Go through the throttle calibration procedure. Teaching the
      esc the min and max values of the throttle.
      Turn off the power, and then back on, while sending a full-throttle
      signal to the ESC through the PWM pin.
      Then wait for 2 sec and send a zero-throttle signal.
      If the 'prog_mode' flag is up, cycle through programming functions
      and interrupt on return key pressed."""
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
          self.start(self._signal_pin, self._duty_min, self._updatefreq)
          self._armed = True


  def disarm(self):
      if not self._armed:
          return
      else:
          print "Disarming ESC " + self._name + "..."
          self.stop(signal_pin)
          self.cleanup()
          self._armed = False

  def normalize(self, duty_value):
      """Map duty cycle range to [0,1]"""
      return (duty_value - self._min)/self._span

  def map(self, speed):
      """Inverse of normalize"""
      return speed*self._span + self._min

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
    

  def set_speed(self, speed=self._speed):
    """ Set the speed as a fraction of the total capacity, 
    expressed as a float in [0,1].
    Examples:
      set_speed(0.10) puts the engine at 10% of maximum power
      set_speed(0.80) puts the engine at 80% of maximum power"""
    self.set_duty(self._signal_pin, map(speed))
    self._speed = speed
    

  def set_abs_speed(self, duty):
    """Set the speed of the motor as an absolute value within the
    ESC range. If a value outside of the min-max range is given
    the value is processed as being the max or min value possible."""
    self.set_duty(duty)
    self._speed = self.normalize(duty)

  def power_up(self):
    """ Turn on external power to the ESC"""
    self.output(self._power_pin, HIGH)
    self._powered = True
    print "ESC " + self._name + " powered up!"

  def power_down(self):
    """ Turn off external power to the ESC"""
    self.output(self._power_pin, LOW)
    self._powered = False
    print "ESC " + self._name + " powered down!"

