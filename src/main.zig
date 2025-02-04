const std = @import("std");
const bin_utils = @import("bin_utils.zig");

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

    const binary = try bin_utils.readBinaryFile(args[1]);
    defer std.heap.page_allocator.free(binary);

    for (binary) |byte| {
        std.debug.print("{b}\n", .{byte});
    }
    return 0;
}
