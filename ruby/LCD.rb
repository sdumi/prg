require 'getoptlong'

class LCD
    attr_accessor( :size, :spacing )

    #
    # This hash is used to define the segment display for the
    # given digit. Each entry in the array is associated with
    # the following states:
    #
    #    HORIZONTAL
    #    VERTICAL
    #     HORIZONTAL
    #     VERTICAL
    #    HORIZONTAL
    #    DONE
    #   
    # The HORIZONTAL state produces a single horizontal line. There
    # are two types:
    #
    #     0 - skip, no line necessary, just space fill
    #    1 - line required of given size
    #
    # The VERTICAL state produces a either a single right side line,
    # a single left side line or a both lines.
    #
    #     0 - skip, no line necessary, just space fill
    #    1 - single right side line
    #    2 - single left side line
    #    3 - both lines
    #
    # The DONE state terminates the state machine. This is not needed
    # as part of the data array.
    #
    @@lcdDisplayData = {
        "0" => [ 1, 3, 0, 3, 1 ], 
        "1" => [ 0, 1, 0, 1, 0 ],
        "2" => [ 1, 1, 1, 2, 1 ],
        "3" => [ 1, 1, 1, 1, 1 ],
        "4" => [ 0, 3, 1, 1, 0 ],
        "5" => [ 1, 2, 1, 1, 1 ],
        "6" => [ 1, 2, 1, 3, 1 ],
        "7" => [ 1, 1, 0, 1, 0 ],
        "8" => [ 1, 3, 1, 3, 1 ],
        "9" => [ 1, 3, 1, 1, 1 ]
    }

    @@lcdStates = [
        "HORIZONTAL",
        "VERTICAL",
        "HORIZONTAL",
        "VERTICAL",
        "HORIZONTAL",
        "DONE"
    ]

    def initialize( size=1, spacing=1 )
        @size = size
        @spacing = spacing
    end

    def display( digits )
        states = @@lcdStates.reverse
        0.upto(@@lcdStates.length) do |i|
sleep 5
            case states.pop
            when "HORIZONTAL"
                line = ""
                digits.each_byte do |b|
                    line += horizontal_segment( @@lcdDisplayData[b.chr][i] )
                end
                print line + "\n"
                   
            when "VERTICAL"
                1.upto(@size) do |j|
                    line = ""
                    digits.each_byte do |b|
                        line += vertical_segment( 
@@lcdDisplayData[b.chr][i] )
                    end
                    print line + "\n"
                end
            when "DONE"
                break
            end
        end
    end

    def horizontal_segment( type )
        case type
        when 1
            return " " + ("-" * @size) + " " + (" " * @spacing)
        else
            return " " + (" " * @size) + " " + (" " * @spacing)
        end
    end

    def vertical_segment( type )
        case type
        when 1
            return " " + (" " * @size) + "|" + (" " * @spacing)
        when 2
            return "|" + (" " * @size) + " " + (" " * @spacing)
        when 3
            return "|" + (" " * @size) + "|" + (" " * @spacing)
        else
            return " " + (" " * @size) + " " + (" " * @spacing)
        end
    end
end

##### Main

opts = GetoptLong.new(
    [ "--size", "-s", GetoptLong::REQUIRED_ARGUMENT ],
    [ "--spacing", "--sp", "-p", GetoptLong::REQUIRED_ARGUMENT ]
)

lcd = LCD.new

opts.each do |opt, arg|
    case opt
    when "--size"
        lcd.size = arg.to_i

    when "--spacing"
        lcd.spacing = arg.to_i
    end
end

lcd.display( ARGV.shift )