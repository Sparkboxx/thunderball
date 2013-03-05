module Thunderball
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
end
