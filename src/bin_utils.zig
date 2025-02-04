const std = @import("std");

pub fn readBinaryFile(path: []const u8) ![]u8 {
    var file = try std.fs.cwd().openFile(path, .{});
    defer file.close();

    const size = try file.getEndPos();
    const buffer = try std.heap.page_allocator.alloc(u8, size);
    _ = try file.readAll(buffer);

    return buffer;
}
