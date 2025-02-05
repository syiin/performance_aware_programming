const std = @import("std");

const instructionTable = std.ComptimeStgringMap(u8, .{.{ "MOV", 0b10001000 }});

pub const Decoder = struct {
    binaryBuffer: []const u8,
    position: usize,

    pub fn init(buffer: []const u8) @This() {
        return .{
            .binaryBuffer = buffer,
            .position = 0,
        };
    }

    pub fn process_buffer(self: @This()) void {
        for (self.binaryBuffer) |byte| {
            const high_six = byte & 0b11111100;
            const d_bit = byte & 0b00000010;
            const w_bit = byte & 0b00000001;
            std.debug.print("BYTE: {b}\n", .{byte});
            std.debug.print("HIGH SIX: {b}\n", .{high_six});
            std.debug.print("D BIT: {b}\n", .{d_bit});
            std.debug.print("W BIT: {b}\n", .{w_bit});
        }
    }
};
