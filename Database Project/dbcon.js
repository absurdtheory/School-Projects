var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : '[host name]',
  user            : '[username]',
  password        : '[password]',
  database        : '[database name]',

 connectTimeout: 60 * 60 * 1000,
 aquireTimeout: 60 * 60 * 1000,
 timeout: 60 * 60 * 1000,

});

module.exports.pool = pool;
