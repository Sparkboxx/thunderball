require 'bundler/setup'
require 'arduino_firmata'
require 'logger'

module Thunderball
  attr_reader :board
  attr_writer :logger

  HIGH = true
  LOW = false

  def self.board=(board)
    @board = board
  end

  def board
    @board ||= Board.new
  end

  def logger
    @logger ||= Logger.new(STDOUT)
  end

  module FirmataHelpers
    attr_reader :board

    def delay(rate)
      board.delay(rate)
    end

    def default_board
      Thunderball.board
    end

    def initialize(opts={})
      opts = defaults.merge(opts)
      opts.each_pair do |key, value|
        write_attribute(key, value)
      end
    end

    private
    def defaults
      {}
    end
  end

  class Blinker
    include FirmataHelpers

    attr_reader :pin, :rate

    def flash
      board.digital_write(pin, HIGH)
      delay(rate)
      board.digital_write(pin, LOW)
      delay(rate)
    end

    def blink(number)
      number.times do |t|
        flash
      end
    end

    private
    def defaults
      { :pin=>13,
        :rate=>0.3,
        :board=>default_board }
    end
  end

  class LDR
    include FirmataHelpers

    attr_reader :pin, :voltage, :circuit_resistance, :ldr_factor

    def read
      board.analog_read(pin)
    end

    def volts
      read * 5 / 1024.to_f
    end

    def lux
      res1 = circuit_resistance
      c1 = ldr_factor

      ((voltage / volts) - 1) * c1 / res1
    end

    private

    def defaults
      { :pin=>2,
        :board=>default_board,
        :voltage=>3.3,
        :circuit_resistance=>1e4.to_f,
        :ldr_factor=>5e5.to_f
      }
    end

  end

  class Board
    include FirmataHelpers

    extend Forwardable
    def_delegators :@board, :digital_write, :analog_read

    attr_reader :board

    def initialize(opts={})
      port = opts[:port] || defaults[:port]
      @board = ArduinoFirmata.connect(port)
    end

    private
    def defaults
      {:port=> '/dev/tty.usbmodemfa131'}
    end

  end
end
