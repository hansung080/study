exports.db = function () {
	var db = {};
	var storage = [];
	var count = 0;

	db.select = function (id) {
		if (id) {
			id = (typeof(id) == 'string') ? Number(id) : id;

			for (var i in storage) {
				if (storage[i].id == id) {
					return storage[i];
				}
			}

		} else {
			return storage;	
		}
	};

	db.insert = function (data) {
		data.id = ++count;
		storage.push(data);
		return data;
	};

	db.update = function (data) {
		id = (typeof(data.id) == 'string') ? Number(data.id) : data.id;
		for (var i in storage) {
			if (storage[i].id == id) {
				storage[i] == data;
				return true;
			}
		}

		return false;
	};

	db.delete = function (id) {
		id = (typeof(id) == 'string') ? Number(id) : id;
		for (var i in storage) {
			if (storage[i].id == id) {
				storage.splice(i, 1);
				return true;
			}
		}

		return false;
	};

	return db;
}();
