#!/bin/python3
from os import mkdir
from os.path import basename
import requests
import re
from bs4 import *

base_url  = "https://girlvspig.com"
index_url = base_url + "/archive"
strip_url = "/images/her{n}{letter}.gif"
out_dir   = "out/"

def get_comic_list():
	r = []
	index = BeautifulSoup(requests.get(index_url).text, 'html.parser')
	for i in index.find('article').find_all('li'):
		i = i.find('a')
		name = i.text.replace(' ', '_')
		n = re.search(r'\d+', name).group()
		r.append({'name' : name, 'n' : n})
	return r

def download_page(c):
	page_dir = out_dir + c['name']

	try: mkdir(page_dir)
	except: pass

	for l in [i for i in ['a', 'b', 'c', 'd']]:
		full_strip_url = base_url + strip_url.format(n=c['n'], letter=l)
		print(full_strip_url)
		response = requests.get(full_strip_url)
		with open(page_dir + "/" + basename(full_strip_url), 'wb') as f:
			f.write(response.content)


for c in get_comic_list(): download_page(c)
