module Thunderball
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
end
