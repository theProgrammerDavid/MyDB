var net = require('net');
//var client = new net.Socket();

class HasherDB{
    client;
    host = '127.0.0.1';
    port = 27015;
    constructor(host='127.0.0.1',port=27015){
        this.host = host;
        this.port = port;
        this.client = new net.Socket();

        try{
            this.client.connect(27015, '127.0.0.1', function () {
                console.log('Connected');
    
            });
            this.client.on('close', function () {
                console.log('Connection closed');
                this.client.destroy();
            });
            this.client.on('data', function (data) {
                console.log('Received: ' + data + '-');
                //client.destroy(); // kill client after server's response
            });
            
        }
        catch(e){
            console.log(e);
        }
    }

    /*
    connect(host='127.0.0.1',port=27015){
        this.host = host;
        this.port = port;
        try{
            this.client.connect(27015, '127.0.0.1', function () {
                console.log('Connected');
    
            });
            this.client.on('close', function () {
                console.log('Connection closed');
                this.client.destroy();
            });
            this.client.on('data', function (data) {
                console.log('Received: ' + data + '-');
                //client.destroy(); // kill client after server's response
            });
            
        }
        catch(e){
            console.log(e);
        }
        
    }
    */
   close(){
       this.client.destroy();
   }
}
module.exports = HasherDB;
/*
function connectClient() {
    client.connect(27015, '127.0.0.1', function () {
        console.log('Connected');

    });
    
}

function setupClient() {
    client = undefined;
    client = new net.Socket();
    client.connect(27015, '127.0.0.1', function () {
        console.log('Connected');
    });
    client.on('close', function () {
        console.log('Connection closed');
        
    });

    client.on('data', function (data) {
        console.log('Received: ' + data + '-');
        //client.destroy(); // kill client after server's response
    });
}

module.exports = {


    HDBSetup: function () {
        client.connect(27015, '127.0.0.1', function () {
            console.log('Connected');

        });
        client.on('close', function () {
            console.log('Connection closed');
            client.destroy();
        });
        client.on('data', function (data) {
            console.log('Received: ' + data + '-');
            //client.destroy(); // kill client after server's response
        });
    }


}

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

function close(){
    client.write('exit');
    client.destroy();
}

function readFromDisk() {
    client.write(JSON.stringify({ protocol: -1 }));
}

function commit() {
    client.write(JSON.stringify({ protocol: 0 }));
}

function addEntry(value) {
    client.write(JSON.stringify({ val: value, protocol: 100 }));
}

function addEntryCheckDup(value) {
    client.write(JSON.stringify({ val: value, protocol: 102 }));
}

function findAll(phoneNo) {
    client.write(JSON.stringify({ val: phoneNo, protocol: 200 }));
}

function findOne(phoneNo) {
    client.write(JSON.stringify({ val: phoneNo, protocol: 201 }));
}

function deleteEntry(phoneNo) {
    client.write(JSON.stringify({ val: phoneNo, protocol: 402 }));
}

//add the modify stuff

function findOneAndUpdate(phoneNo, newData) {
    client.write(JSON.stringify({ val: { phoneNo: phoneNo, data: newData }, protocol: 301 }));
}

function findAllAndUpdate(phoneNo, newData) {
    client.write(JSON.stringify({ val: { phoneNo: phoneNo, data: newData }, protocol: 300 }));
}

*/