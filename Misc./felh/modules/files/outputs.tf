output "file_names" {
  description = "The names of the generated files"
  value       = [for i in range(var.file_count) : "${var.file_prefix}${i}${var.file_extension}"]
}

output "file_count" {
  value       = var.file_count
}
