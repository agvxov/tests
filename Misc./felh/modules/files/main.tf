
resource "null_resource" "generate_files" {
  count = var.file_count

  triggers = {
    timestamp = timestamp()
  }

  provisioner "local-exec" {
    command = <<-EOT
      echo "Content of file ${path.module}${count.index}${var.file_extension}" > ${path.module}/${var.file_prefix}${count.index}${var.file_extension}
    EOT
  }
}
