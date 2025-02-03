locals {
  output_prefixes = {
    for key, value in var.input_value : "prefixed_${key}" => value
  }
}

output "prefixed_outputs" {
  value = local.output_prefixes
}

#output "processed_input" {
#  description = "The input received from the files module with a prefix of 'read-'"
#  value       = "read-${var.input_value}"
#}
