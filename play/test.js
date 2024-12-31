function main(){
  let a = 1;
  let b = () => 2
  let map = new Map();
  map.set('key1',a+b())
  console.log('main',map.get('key1'))
}

main();