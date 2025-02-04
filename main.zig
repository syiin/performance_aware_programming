const std = @import("std");

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

    const binary = try readBinaryFile(args[1]);
    defer std.heap.page_allocator.free(binary);

    for (binary) |byte| {
        std.debug.print("{b}\n", .{byte});
    }
    return 0;
}

pub fn readBinaryFile(path: []const u8) ![]u8 {
    var file = try std.fs.cwd().openFile(path, .{});
    defer file.close();

    const size = try file.getEndPos();
    const buffer = try std.heap.page_allocator.alloc(u8, size);
    _ = try file.readAll(buffer);

    return buffer;
}
