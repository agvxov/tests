# Netc(h)at
> minimalist webchat where the client is any generic netcat implementation

I wrote this for fun, because of someone's influence.

Versions:
+ **netchat.full.py**: original version; was too easy to write
+ **netchat.min.py**: modified version of *full* with various tricks deployed to make it as short (in character and line count) as possible
+ **netchat.balance.py**: modified version of *full* which uses ASCII escape codes to manipulate the cursor in such ways to not interupt message typing by printing incoming messages over yours

To run the server:
```Bash
$ python3 net_chat.min.py 12345
```

To join:
```Bash
$ nc 127.0.0.1 12345
```

That, or have more fun using Tor tunneling.

---

This project works,
it has been retired because it has no future.
