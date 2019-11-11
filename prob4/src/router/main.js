var xmljs = require('xml-js');

module.exports = function(app)
{
	var options = {compact: true, trim: true, commentFn: function(val){ return (new Function(val))();}};
	var destroyedCountry = [];

	app.get('/', function(req, res) {
		res.render('index.html');
	});

	app.post('/f', function(req, res) {
		console.log(req.body);
		var resdata = "";
		var targetCountryId = "";
		try {
			var obj = JSON.parse(xmljs.xml2json(req.body, options));
			targetCountryId = obj.fire.target._text;
			if(destroyedCountry.indexOf(targetCountryId) >= 0) {
				resdata = {'result': 'dup', 'echo_verify': obj };
			}
			else {
				var result = Math.floor(Math.random() * 2);
				if(result == 0) {
					resdata = {'result': 'fail', 'message': 'Nuclear weapon trouble.', 'echo_verify': obj };
				}
				else {
					destroyedCountry.push(targetCountryId);
					resdata = {'result': 'success', 'echo_verify': obj };
				}
			}
		}
		catch(err) {
			console.log(err.message);
			resdata = {'result': 'err', 'message': 'system error..', 'echo_verify': obj};
		}
		console.log(resdata);
		res.json(resdata);
	});

}
