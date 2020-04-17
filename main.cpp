#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <chrono>
using namespace std::chrono;

template<typename T>
void print_vec(const std::vector<T>& v, int start = 0, int size = -1){
  if(size == -1)
    size = v.size();
  int end = start + size;
  for(int i = start; i < end; i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;
}

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return ~hash1 ^ hash2;
    }
};



bool operator== (const std::pair<int, int>& p1, const std::pair<int, int>& p2)  {
  return (p1.first == p2.first && p1.second == p2.second);
}


/*
bool operator!= (const std::pair<int, int>& p1, const std::pair<int, int>& p2)  {
  return !(p1 == p2);
}
*/ 

// template<class T1 = int, class T2 = int>
bool operator<= (const std::pair<int, int>& p1, const std::pair<int, int>& p2)  {
  if(p1 == p2) return true;
  if(p1.first < p2.first) return true;
  if(p1.first == p2.first && p1.second < p2.second) return true;
  return false;
}


// template<class T1, class T2>
bool operator>= (const std::pair<int, int>& p1, const std::pair<int , int>& p2)  {
  if(p1 == p2) return true;
  if(p1.first > p2.first) return true;
  if(p1.first == p2.first && p1.second > p2.second) return true;
  return false;
}


// template<class T1, class T2>
bool operator> (const std::pair<int , int>& p1, const std::pair<int , int>& p2)  {
  if(p1.first > p2.first) return true;
  if(p1.first == p2.first && p1.second > p2.second) return true;
  return false;
}


// template<class T1, class T2>
bool operator< (const std::pair<int , int>& p1, const std::pair<int , int>& p2)  {
  if(p1.first < p2.first) return true;
  if(p1.first == p2.first && p1.second < p2.second) return true;
  return false;
}




template<typename T>
void merge(std::vector<T>& v, std::vector<T>& lv, std::vector<T>& rv , int start, int size){
  int l = 0, r = 0, k = start, end = start+size;
  while(k < end){
    while(l < lv.size() && lv[l] <= rv[r]){
      v[k] = lv[l];l++;k++;
    }
    while(r < rv.size() && lv[l] > rv[r]){
      v[k] = rv[r];r++;k++;
    }
    if(l >= lv.size() || r >= rv.size())
      break;
  }
  while(k < end && l < lv.size()){
    v[k] = lv[l];l++;k++;
  }
  while(k < end && r < rv.size()){
    v[k] = rv[r];r++;k++;
  }
}


template<typename T>
void merge_sort(std::vector<T>& v, int start = 0, int size = -1){
  if(size == -1) size = v.size();
  int left_size = size/2;
  int right_size = size - left_size;
  int left = start;
  int right = start + left_size;
  if(size <= 1){
    return;
  }
  merge_sort(v, left, left_size);
  merge_sort(v, right, right_size);
  std::vector<T> left_vec(left_size);
  std::vector<T> right_vec(right_size);
  for(int i = 0; i < left_size; i++)
    left_vec[i] = v[left+i];
  for(int i = 0; i < right_size; i++)
    right_vec[i] = v[right+i];

  merge(v, left_vec, right_vec, start, size);
  
}


class SuffixArray{
  private:
    std::vector<int> m_arr;
    std::string m_str;

  public:
    SuffixArray(const std::string& str)
      : m_arr( std::vector<int>(str.size() + 1)), m_str( str ) 
    {
      /*
      // make the string a vector of characters
      std::vector<char> m_ch(str.size());
      for(int i = 0; i < str.size(); i++)
        m_ch[i] = str[i];

      // sort the characters
      merge_sort(m_ch, 0, m_ch.size());
      print_vec(m_ch);
      std::cout << std::endl;
      */

      // encode chars

      std::vector<int> a(m_arr.size());
      a = encode_str(a, str);
      for(int i = 1; i < str.size(); i *= 2){
        std::vector<std::pair<int,int>> paired(a.size(), {0,0});
        pairing(paired , a, i);
        a = encode_pairs(paired, a);
      }
      for(int i = 0; i < a.size(); i++){
        m_arr[a[i]] = i;
      }
      // print_vec(m_arr);
    }
    std::vector<int>& encode_pairs(std::vector<std::pair<int, int>>& p, std::vector<int>& a){
      std::vector<std::pair<int,int>> temp_p = p;
      merge_sort<std::pair<int, int>>(temp_p);
      // std::unordered_map<std::pair<int,int>, int, hash_pair> encoding_map;
      std::map<std::pair<int,int>, int> encoding_map;
      for(int i = 0, k = 0; i < temp_p.size(); i++){
        auto find_pair = encoding_map.find(temp_p[i]);
        if(find_pair != encoding_map.end()) continue;
        encoding_map.insert({temp_p[i], k});
        k++;
      }
      for(int i = 0; i < a.size(); i++){
        a[i] = encoding_map[p[i]];
      }
      return a;
    }
    void pairing(std::vector<std::pair<int,int>>& p, std::vector<int>& a, int l){
      for(int i = 0; i < a.size(); i++){
        if(i+l >=  a.size()) p[i] = std::make_pair(a[i],0);
        else p[i] = std::make_pair(a[i],a[i+l]);
      }
    }
    std::vector<int>& encode_str(std::vector<int>& a, const std::string& str){
      // std::cout << str << "\n"; 
      std::vector<bool> ch_in_str('z'-'a');
      for(int i = 0; i < str.size(); i++)
        ch_in_str[str[i]-'a'] = true;
      // print_vec<bool>(ch_in_str);
      std::vector<int> encoding('z'-'a');
      for(int i = 0, k = 1; i < encoding.size(); i++){
        if(ch_in_str[i]){
          encoding[i] = k;
          k++;
        }

      }
      // print_vec<int>(encoding);
      for(int i = str.size(); i >= 0; i--){
        a[i] = encoding[str[i]-'a'];
      }
      // print_vec<int>(a);
      return a;
    }
    std::vector<int>& arr() { return m_arr; }
    void print() const {
      // std::cout << "printing the array \n";
      for(int i = 0; i < m_arr.size(); i++){
        std::cout << m_arr[i] << " ";
      }
      std::cout << std::endl;
    }
};


int
main(){
  // std::cout << "This program is transforming a string to a suffix array!! \n";
  std::string input; // = "baccccacaabc";
  int n = 1;
  std::cin >> n;
  for(int i = 0; i < n; i++){
    std::cin >> input;
    // auto start = high_resolution_clock::now();
    SuffixArray sa(input);
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // std::cout << duration.count() << " microsecs " << std::endl;
    sa.print();
  }
  return 1;
}
