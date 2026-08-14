from bing_image_downloader import downloader
from config import *

output_dir = "dataset/"

for category in [category_a, category_b]:
	downloader.download(
		category,
		limit=from_n_images,
		output_dir=output_dir,
		timeout=60,
	)
