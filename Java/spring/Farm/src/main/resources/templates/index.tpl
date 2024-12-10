yieldUnescaped '<!DOCTYPE html>'
html(lang:'en') {
	body {
		div {
			h1 { yield 'Index' }
		}

		div {
			a (href: '/list') {
				button {
					yield 'list'
				}
			}
		}

		div {
			a (href: '/login') {
				button {
					yield 'login'
				}
			}
		}

		div {
			a (href: '/secret') {
				button {
					yield 'secret'
				}
			}
		}
	}
}
