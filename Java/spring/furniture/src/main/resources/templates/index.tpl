yieldUnescaped '<!DOCTYPE html>'
html(lang:'en') {
	body {
		div {
			h1 { yield(title) }
		}
		ul {
			furnitures.findAll().each { furniture ->
				li {
					yield "${furniture.name}"
				}
			}
		}

		div {
			h4 { yield 'Add new' }
			form (method: 'post', enctype: 'application/json') {
				input (name: "name", placeholder: "name") { } br {}
				button (type: 'submit') { yield 'Submit' }
			}
		}
	}
}
