exports.db = function () {
	var db = {};
	var users = [];
	var count = 0;

	db.select = function (id) {
		if (id) {
			id = (typeof(id) == 'string') ? Number(id) : id;

			for (var i in users) {
				if (users[i].id == id) {
					return users[i];
				}
			}

		} else {
			return users;	
		}
	};

	db.insert = function (user) {
		user.id = ++count;
		users.push(user);
		return user;
	};

	db.update = function (user) {
		id = (typeof(user.id) == 'string') ? Number(user.id) : user.id;
		for (var i in users) {
			if (users[i].id == id) {
				if (user.name) {
					users[i].name = user.name;
				}

				if (user.age) {
					users[i].age = user.age;
				}

				return users[i];
			}
		}

		return {};
	};

	db.delete = function (id) {
		id = (typeof(id) == 'string') ? Number(id) : id;
		for (var i in users) {
			if (users[i].id == id) {
				users.splice(i, 1);
				return users;
			}
		}

		return userss;
	};

	return db;
}();
