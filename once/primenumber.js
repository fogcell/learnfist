'use strict';

function get_primes(arr) {
 arr = arr.filter(function (x) {
    if(x===1){
        return false;
    }else{
        for(var i=2;i<=Math.sqrt(x);i++){
            if(x%i===0){
                return false;
            }            
        }
       return true;
    }
});
return arr;
}

// 测试:
var
    x,
    r,
    arr = [];
for (x = 1; x < 100; x++) {
    arr.push(x);
}
r = get_primes(arr);
if (r.toString() === [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97].toString()) {
    alert('测试通过!');
} else {
    alert('测试失败: ' + r.toString());
}
