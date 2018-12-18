var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs340_tuckera6',
  password        : '5156',
  database        : 'cs340_tuckera6',

 connectTimeout: 60 * 60 * 1000,
 aquireTimeout: 60 * 60 * 1000,
 timeout: 60 * 60 * 1000,

});

module.exports.pool = pool;
