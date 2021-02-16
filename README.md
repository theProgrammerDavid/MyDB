# My Database Project

This is a really old Database Management Systems project where I made my own databasein C++ (<strong>Windows only</strong>). I had intended for it to be a general purpose database with user defined types, but alas, my [friend](https://github.com/codevaam) and i made it under a week, and so, corners had to be cut.

HasherDB (since we had just been taught hash tables) is designed around a 'Blood Bank' with basic CRUD operations.

> HasherDB is a database (like MongoDB, Mysql, etc), and as such, the NodeJS driver has been provided in `api.js`. Since it uses sockets, the driver can be implemented in any language

HasherDB uses ``std::threads`` and each client spawns one thread for itself.

The fields of each document is as follows:
```json

var person = {
    name: "David",
    pswd: "password",
    blood_group: "B",
    phoneNo: "9722335128",
    donorName: "John",
    donorFather: "Jack",
    transferDate: "12Mar2000",
    age: 22,
    sex: 'M',
}
```
You can then connect to the db with:

```js

function connectClient() {
    client.connect(27015, '127.0.0.1', function () {
        console.log('Connected');

    });
    
}

function setupClient() {
    client.connect(27015, '127.0.0.1', function () {
        console.log('Connected');

    });

    client.on('data', function (data) {
        console.log('Received: ' + data + '-');
    });
}

```

## Requirements
* Windows and Visual Studio C++ Compiler to build
* NodeJS to use the api provided
* compile with C++ 11 Release Mode and link to ``Ws2_32.lib ``
