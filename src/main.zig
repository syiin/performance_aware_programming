const std = @import("std");
const bin_utils = @import("bin_utils.zig");
const decoder = @import("decoder.zig");

pub fn main() !u8 {
    // Get an allocator
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const args = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, args);

    // Check args
    if (args.len < 2) {
        std.debug.print("Usage: {s} <filename>\n", .{args[0]});
        return 1;
    }

    // Read file and process it
    const binary = try bin_utils.readBinaryFile(allocator, args[1]);
    defer allocator.free(binary);

    var _decoder = decoder.Decoder.init(binary);
    _decoder.process_buffer();
    return 0;
}
