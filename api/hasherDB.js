var net = require('net');
//var client = new net.Socket();

class HasherDB{
    host;
    port = 2;
    client = new net.Socket();
    
    constructor(host='127.0.0.1',port=27015){
        this.host = host;
        this.port = port;

        try{
            this.client.connect(this.port, this.host, function () {
                console.log('Connected');
    
            });
            this.client.on('close', function () {
                console.log('Connection closed');
            });
            this.client.on('data', function (data) {
                console.log('Received: ' + data + '-');
            });
            
        }
        catch(e){
            console.log(e);
        }
    }
   
 close(){
    this.client.write('exit');
    //this.client.destroy();
}

 readFromDisk() {
    this.client.write(JSON.stringify({ protocol: -1 }));
}

 commit() {
    this.client.write(JSON.stringify({ protocol: 0 }));
}

 addEntry(value) {
    this.client.write(JSON.stringify({ val: value, protocol: 100 }));
}

 addEntryCheckDup(value) {
    this.client.write(JSON.stringify({ val: value, protocol: 102 }));
}

 findAll(phoneNo) {
    this.client.write(JSON.stringify({ val: phoneNo, protocol: 200 }));
}

 findOne(phoneNo) {
    this.client.write(JSON.stringify({ val: phoneNo, protocol: 201 }));
}

 deleteEntry(phoneNo) {
    this.client.write(JSON.stringify({ val: phoneNo, protocol: 402 }));
}

//add the modify stuff

 findOneAndUpdate(phoneNo, newData) {
    this.client.write(JSON.stringify({ val: { phoneNo: phoneNo, data: newData }, protocol: 301 }));
}

 findAllAndUpdate(phoneNo, newData) {
    this.client.write(JSON.stringify({ val: { phoneNo: phoneNo, data: newData }, protocol: 300 }));
}
}
module.exports = HasherDB;
