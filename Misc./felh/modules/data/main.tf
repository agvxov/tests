locals {
  file_number = 1
}

data "local_file" "file_data" {
  filename = var.path
}
