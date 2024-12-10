import requests
import bs4
import re

base_url = "http://www.asciiartfarts.com/"
hub_url  = "http://www.asciiartfarts.com/number.html"
out_dir  = "out/"

hub = bs4.BeautifulSoup(requests.get(hub_url).text, 'html.parser')

href_list = set()

for a in hub.find('ul').find('li').find_all('a'):
	try: href = a['href']
	except: continue
	if re.match(r'\d+.html', href):
		href_list.add(href)

#print(href_list)

for h in href_list:
	page = bs4.BeautifulSoup(requests.get(base_url + h).text, 'html.parser')
	name = (page
			.find('h1')
			.text.split(':')[1]
			.strip()
			.replace(' ', '_')
			.replace('/', '_')
			+ '.ascii'
	)
	ascii_art = page.find_all('pre')[1].text
	print(name)
	with open(out_dir + name, 'w') as f: f.write(ascii_art)
