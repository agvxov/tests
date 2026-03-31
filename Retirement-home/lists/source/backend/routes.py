from globals import *
from flask import render_template

# XXX: move
import database as db
app.template_folder = 'templates/'

@app.route('/')
def hello_world():
	with db.connection() as connection:
		cur = connection.cursor()
		movies = cur.execute('SELECT * FROM movie;').fetchall()
		print(movies[0])
		return render_template('index.html', movies=movies)
