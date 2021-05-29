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