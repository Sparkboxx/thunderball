require 'bundler/setup'
require 'firmata'

module ArduinoFirmata
  attr_reader :board

  HIGH = Firmata::Board::HIGH
  LOW = Firmata::Board::LOW

  def self.board=(board)
    @board = board
  end

  def board
    @board ||= Board.new
  end

  module FirmataHelpers
    def delay(rate)
      board.delay(rate)
    end

    def default_board
      ArduinoFirmata.board
    end
  end

  class Blinker
    include FirmataHelpers

    attr_reader :board, :pin, :rate

    def initialize(opts={})
      opts = defaults.merge(opts)
      @board = opts[:board]
      @pin = opts[:pin]
      @rate = opts[:rate]
    end

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

  class Board
    include FirmataHelpers

    extend Forwardable
    def_delegator :@board, :digital_write

    attr_reader :board

    def initialize(opts={})
      port = opts[:port] || defaults[:port]

      @board = Firmata::Board.new(port)
      board.connect
    end

    private
    def defaults
      {:port=> '/dev/tty.usbmodemfa131'}
    end

  end
end
