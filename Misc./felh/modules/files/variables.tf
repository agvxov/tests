
variable "file_count" {
  description = "The number of files to be created"
  type        = number
  default     = 1
}

variable "file_prefix" {
  description = "The prefix for the filenames"
  type        = string
  default     = "file"
}

variable "file_extension" {
  description = "The extension for the filenames"
  type        = string
  default     = ".txt"
}
