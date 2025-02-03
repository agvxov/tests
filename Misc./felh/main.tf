module "files" {
  source      = "./modules/files"
  file_count  = 5
}

module "read" {
  source       = "./modules/read"
  input_value  = module.files.file_names
}

variable "answer_1" {}
variable "answer_2" {}
variable "answer_3" {}
variable "answer_4" {}
variable "answer_5" {}
module "write" {
  source       = "./modules/write"
  answer_1 = var.answer_1
  answer_2 = var.answer_2
  answer_3 = var.answer_3
  answer_4 = var.answer_4
  answer_5 = var.answer_5
}



output "read_output" {
	#value = module.read.processed_input
	value = module.read.prefixed_outputs
}

output "answers" {
	value = module.write.all_variables
}

module "data" {
  source     = "./modules/data"
  depends_on = [module.files]
  file_count = module.files.file_count
  path = "${path.root}/modules/files/file1.txt"
}

output "file_id" {
  description = "The ID of the file"
  value       = module.data.file_id
}
