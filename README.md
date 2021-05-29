# My Database Project

This is a really old Database Management Systems project where I made my own databasein C++ (<strong>Windows only</strong>). I had intended for it to be a general purpose database with user defined types, but alas, my [friend](https://github.com/codevaam) and i made it under a week, and so, corners had to be cut.

HasherDB (since we had just been taught hash tables) is designed around a 'Blood Bank' with basic CRUD operations.

> HasherDB is a database (like MongoDB, Mysql, etc), and as such, the NodeJS driver has been provided in `./api/hasherDB.js`. Since it uses sockets, the driver can be implemented in any language

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
const db = require('./api/hasherDB');

const DB = new db('localhost',27011);
```
You can then use the API with the functions in `./api/hasherDB.js`

```js
const db = require('./api/hasherDB');

const DB = new db('localhost',27011);

var person = {
    name:"David",
    pswd:"password",
    blood_group:"B",
    phoneNo:"9999999999",
    donorName: "John",
    donorFather: "Jack",
    transferDate: "22Jan2000",
    age: 22,
    sex: 'M',
}

var person2 = {
    name:"DavidVelho",
    pswd:"password",
    blood_group:"B",
    phoneNo:"9999999999",
    donorName: "John",
    donorFather: "Jack",
    transferDate: "22Jan2000",
    age: 22,
    sex: 'M',
}

DB.addEntry(person);
DB.addEntry(person2);
DB.addEntryCheckDup(person);

DB.close();
```
## Requirements
* Windows and Visual Studio C++ Compiler to build
* NodeJS to use the api provided
* compile with C++ 11 Release Mode and link to ``Ws2_32.lib ``
