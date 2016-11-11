var mongoose = require('mongoose');
    Schema = mongoose.Schema;

// URL Model
// Schema: url, tinyUrl, date created
var urlSchema = new Schema({
    url: String,
    tiny_url: String,
    updated_at: { type: Date, default: Date.now }
});

module.exports = mongoose.model('Url', urlSchema);