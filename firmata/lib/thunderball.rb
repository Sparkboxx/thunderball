require 'bundler/setup'
require 'arduino_firmata'
require 'forwardable'

if !$:.include?(File.expand_path('../', __FILE__))
  $:.unshift(File.expand_path('../', __FILE__))
end

require 'thunderball/helpers/firmata'
require 'thunderball/board'
require 'thunderball/ldr'
require 'thunderball/blinker'

module Thunderball
  HIGH = true
  LOW = false

  def self.board=(board)
    @board = board
  end

  def board
    @board ||= Board.new
  end
end
