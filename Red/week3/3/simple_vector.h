#pragma once

#include <cstdlib>
#include<algorithm>

// Р РµР°Р»РёР·СѓР№С‚Рµ С€Р°Р±Р»РѕРЅ SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector():
	  size(0),
	  capa(0){
	  data = nullptr;
	  _end = data +1;
  }
  explicit SimpleVector(size_t size):
	  size(size),
	  capa(size){
	  data = new T [size];
	  _end = data + size;
  }
  ~SimpleVector(){
	  delete[] data;
  }


  void Copy(T* o_start,T* n_start){
	  for(size_t i = 0 ; i < size ; i++)
		  *(n_start+i) = *(o_start+i);
  }

  T& operator[](size_t index){
	  return data[index];
  }

  T* begin(){
	  if(data != nullptr)
		  return data;
	  return _end;
  }
  T* end(){
	  return _end;
  }
  const T* begin() const{
	  if(data != nullptr)
		  return data;
	  return _end;
   }
   const T* end() const {
 	  return _end;
   }

  size_t Size() const{return size;}
  size_t Capacity() const{return capa;}
  void PushBack(const T& value){
	  if(capa == 0){
		  data = new T[1];
		  _end = data +1;
		  *data = value;
		  size++;
		  capa++;
	  }
	  else if(size == capa){
		  T*swap = new T[size];
		  Copy(data,swap);
		  delete[] data;
		  data = new T[2*capa];
		  Copy(swap,data);
		  delete[] swap;
		  capa*=2;
		  size++;
		  data[size-1] = value;
		  _end = data +size;
	  }
	  else{
		  size++;
		  data[size-1] = value;
		  _end = data + size;
	  }
  }

private:
  T* data;
  T* _end;
  size_t size;
  size_t capa;
};
