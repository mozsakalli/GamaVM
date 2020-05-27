"use strict";

function test(lI0){
var flow=0,lI1,lI2,lI3,lI4,lO2,sI0,tS0,tI6,tI5,tI8,tS1,tI7,tI0,tI2,tI1,tI4,tI3;
while(true) outer: switch(flow){
case 0:
lI1 = lI0
lI2 = 0

case 4:
if(lI2>=100000){flow=112;break outer;}

case 10:
lI3 = 0
lI4 = 100
tI0 = lI2%10
if(tI0!=0){flow=28;break outer;}

case 23:
lI3 = 1
{flow=30;break outer;}

case 28:
lI3 = 2

case 30:
tI1 = lI2%90
if(tI1==0) {flow=60;break outer;}
if(tI1==1) {flow=70;break outer;}
flow=73;break outer;


case 60:
sI0 = lI4

case 62:
tI2 = sI0+1
tS0 = /*S*/tI2
lI4 = tS0
{flow=78;break outer;}

case 70:
lI3+=1

case 73:
tI3 = lI3+lI4
lI3 = tI3

case 78:
tI4 = lI2%50
if(tI4!=0){flow=93;break outer;}

case 85:
tI5 = lI4+10
tS1 = /*S*/tI5
lI4 = tS1

case 93:
tI6 = lI2+lI3
tI7 = lI2*2
tI8 = tI6+tI7
tI6 = tI8+lI4
tI8 = lI1+tI6
lI1 = tI8
lI2+=1
{flow=4;break outer;}

case 112:
{flow=116;break outer;}

case 115:
lO2 = __caught

case 116:
return lI1

}}

function test_native(param) {
    var v = param;
    for(var i=0; i<100000; i++) {
        var add = 0;
        var add2 = 100;
        if(i%10 == 0) add = 1; else add = 2;
        switch(i%90) {
            case 0: add2++;break;
            case 1: add++;
            default: add += add2;
        }
        if(i%50 == 0) add2 += 10;
        v += i+add+i*2+add2;
    }
    return v;
}

var time=new Date().getTime();
var ret=test(0);
time = new Date().getTime()-time;
console.log(ret+" took "+time);

time=new Date().getTime();
ret=test_native(0);
time = new Date().getTime()-time;
console.log(ret+" took "+time);

time=new Date().getTime();
ret=test(0);
time = new Date().getTime()-time;
console.log(ret+" took "+time);

time=new Date().getTime();
ret=test_native(0);
time = new Date().getTime()-time;
console.log(ret+" took "+time);

/*
time=new Date().getTime();
ret=test2(0);
time = new Date().getTime()-time;
console.log(ret+" took "+time);


*/





