import BP from './blackpink.json' assert { type: "json" };

let blackpink = {
  lisa: { name: "Lalisa Manoban", age: 25 },
  jennie: { name: "Kim Jennie", age: 26 },
  jisoo: { name: "Kim Jisoo", age: 27 },
  rose: { name: "박채영", age: 25 }
};

console.log(Object.values(blackpink));
console.log(Object.keys(blackpink));
console.log(Object.entries(blackpink));
console.log(Object.values(BP));
console.log(Object.keys(BP));
console.log(Object.entries(BP));

console.log("-------- JS Object Key ------------");
Object.keys(blackpink).forEach(key => {
  console.log(`${blackpink[key].name}, ${blackpink[key].age}`);
});

console.log("-------- JS Object Value ----------");
Object.values(blackpink).forEach(varl => {
  console.log(`${varl.name}, ${varl.age}`);
});

console.log("-------- JS for..of ---------------");
for (const i of Object.entries(blackpink)) {
  console.log(`${i[1].name}, ${i[1].age}`);
}

console.log("-------- JS for..in ---------------");
for (const i in blackpink) {
  console.log(`${blackpink[i].name}, ${blackpink[i].age}`);
}

console.log("-------- JSON Object Key ----------");
Object.keys(BP).forEach(json_key => {
  console.log(`${BP[json_key].name}, ${BP[json_key].age}`);
});

console.log("-------- JSON Object Value---------");
Object.values(BP).forEach(json_value => {
  console.log(`${json_value.name}, ${json_value.age}`);
});