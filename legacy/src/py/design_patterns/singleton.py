import json

class Singleton:
    __instance = None
    
    @classmethod
    def __get_instance(cls):
        return cls.__instance
    
    @classmethod
    def instance(cls, *args, **kargs):
        cls.__instance = cls(*args, **kargs)
        cls.instance = cls.__get_instance
        return cls.__instance

class Person(Singleton):
    def __init__(self, name, age):
        self.__name = name
        self.__age = age
    
    @property
    def name(self):
        return self.__name
    
    @name.setter
    def name(self, name):
        self.__name = name
    
    @property
    def age(self):
        return self.__age
    
    @age.setter
    def age(self, age):
        self.__age = age
    
    def to_json(self):
        return json.dumps({
            'name': self.__name,
            'age': self.__age
        })
    
    def __str__(self):
        return self.to_json()

def main():
    p = Person.instance('kwon', 34)
    print(p)
    
    p2 = Person.instance()
    print(p2)
    
    p3 = Person.instance()
    print(p3)

if __name__ == '__main__':
    main()

