# Tor wayland fix

> [!IMPORTANT]
> The bug seems to be fixed as of 2025 oct.

Plug'n'play solution for this issue:
https://gitlab.torproject.org/tpo/applications/tor-browser/-/issues/40693

-where wayland is required as a gotcha dependency.
This bug is most relevant on Gentoo systems and has been neglected for years now.

#### Quote from the ticket:
> Potential Wayland dependency
> Closed (moved) Issue created
> We received a report that Tor Browser 11.0 now fails to start on a (Gentoo) Linux machine that does not have Wayland installed. Firefox 91.3.0esr does start.


### Usage
 1. Clone the repo into your tor installation, right by the "start-tor-browser.desktop" file.
 2. Invoke make:
```
 	$ make
```
 3. Start tor using the fixed launcher using the patch
```
 	./start-tor-browser.fix.desktop
```

### Retirement
The bug **is** fixed and there was no regression in the past 9 months.
As such, this monkey-patch is no longer useful.
