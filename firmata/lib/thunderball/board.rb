module Thunderball
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
