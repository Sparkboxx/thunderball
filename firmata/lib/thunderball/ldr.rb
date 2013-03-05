module Thunderball
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
end
