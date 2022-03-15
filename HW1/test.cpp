#include<iostream>
#include<vector>
using namespace std;

const int maxint = 999999;

class input{
  int numNodes;
  int numDsts;
  int numLinks;
  vector<int> Dsts;
  vector<vector<int>> graph1;
  vector<vector<int>> graph2;
public:
    void setdata(int a,int b,int c){
      numNodes = a;
      numDsts = b;
      numLinks = c;
    }
    void setDsts(int Dst){
      Dsts.push_back(Dst);
    }
    void init(int numNodes){
      for(int i=0 ; i<numNodes ; i++){
        vector<int> tmp1,tmp2;
        graph1.push_back(tmp1);
        graph2.push_back(tmp2);
        for(int j=0 ; j<numNodes ; j++){
          graph1[i].push_back(maxint);
          graph2[i].push_back(maxint);
        }
        
      }
    }
    void setGraph1(int index,int neighbor,int digit){
      graph1[index][neighbor] = digit;
      graph1[neighbor][index] = digit;
    }
    void setGraph2(int index,int neighbor,int digit){
      graph2[index][neighbor] = digit;
      graph2[neighbor][index] = digit;
    }
    int getnumNodes(){return numNodes;};
    int getnumDsts(){return numDsts;};
    int getnumLinks(){return numLinks;};
    vector<int> getDsts(){return Dsts;};
    vector<vector<int>> getGraph1(){return graph1;};
    vector<vector<int>> getGraph2(){return graph2;};
};

int ShortestPath(int start,int dest,int IDT,class input Data);

int main()
{
  //呼叫class物件
  input Data;

  int numNodes,numDsts,numLinks;
  cin >> numNodes >> numDsts >>numLinks;
  //輸入數量資料
  Data.setdata(numNodes,numDsts,numLinks);
  //輸入目的地資料
  for(int i=0 ; i<numDsts ; i++){
    int tmp;
    cin >> tmp;
    Data.setDsts(tmp);
  }
  //將vector graph 初始化
  Data.init(numNodes);
  int index = 0,neighbor = 0,digit = 0;
  //將輸入變成對應的矩陣graph
  for(int idx=0 ; idx<numLinks ; idx++){
    for(int col=0 ; col<5 ; col++){
      int tmp;
      cin >> tmp;
      if(col == 1)
        index = tmp;
      else if(col == 2)
        neighbor = tmp;
      else if(col == 3){
        digit = tmp;
        Data.setGraph1(index,neighbor,digit);
      }
      else if(col == 4){
        digit = tmp;
        Data.setGraph2(index,neighbor,digit);
      }
    }
  }

//將graph印出來偵錯
/*  for(int i=0 ; i<numNodes ; i++){
    for(int j=0 ; j<numNodes ; j++)
      cout << Data.getGraph1()[i][j] << " ";
    cout << endl;
  }*/

  int reoccur[numNodes][numNodes];
  
  for(int idx=0 ; idx<numNodes ; idx++){
    cout << idx << endl;
    for(int i=0 ; i<numNodes ; i++)
    reoccur[idx][i] = 0;
    for(int i=0 ; i<numDsts ; i++){
      if(idx != Data.getDsts()[i]){
        int result1 = ShortestPath(idx,Data.getDsts()[i],1,Data);
        cout << Data.getDsts()[i] << " " << result1 << endl;
        int result2 = ShortestPath(idx,Data.getDsts()[i],2,Data);
        if(result1 == result2)
          reoccur[idx][Data.getDsts()[i]] = 1;
      }
    }
  }

  //印出"新"graph的table，但與"舊"重複的要去除掉
  for(int idx=0 ; idx<numNodes ; idx++){
    int times = 0;
    for(int i=0 ; i<numDsts ; i++){
      //去除掉"起點與終點相同"的case
      if(idx != Data.getDsts()[i]){
        if(!reoccur[idx][Data.getDsts()[i]]){
          if(!times)
            cout << idx << endl;
          times++;
          int result2 = ShortestPath(idx,Data.getDsts()[i],2,Data);
          cout << Data.getDsts()[i] << " " << result2 << endl;
        }
      }
    }
  }

}

int ShortestPath(int start,int dest,int IDT,class input Data){
  vector<int> table;
  vector<vector<int>> graph;
  //選擇舊/新的graph
  if(IDT == 1)
    graph = Data.getGraph1();
  else if(IDT == 2)
    graph = Data.getGraph2();

  //將原點(Start)的相鄰相應距離呈現為table
  for(int i=0 ; i<(int)graph[start].size() ; i++){
      table.push_back(graph[start][i]);
  }
  table[start] = maxint;

  //設立closed閘門,先將原點關好
  int closed[table.size()];
  for(int i=0 ; i<(int)table.size() ; i++){
    if(i == start)
      closed[i] = 1;
    else
      closed[i] = 0;
  }
  
  int prev[(int)table.size()];
  for(int i=0 ; i<(int)table.size() ; i++){
    if(table[i] == maxint)
      prev[i] = -1;
    else
      prev[i] = start;
  }
  table[start] = 0;

/*
  vector<vector<int>> path;
  //將path初始化
  for(int i=0 ; i<(int)table.size() ; i++){
    vector<int> tmp;
    path.push_back(tmp);
    path[i].push_back(start);
  }
  //把path的每個開頭都定好
  for(int i=0; i<(int)table.size() ; i++){
    if(graph[start][i] != maxint)
      path[i].push_back(i);
    else
      path[i].push_back(maxint);
  }*/
  //path的偵錯
  /*for(int i=0; i<(int)table.size() ; i++){
    for(int j=0 ; j <(int)table.size() ; j++)
      cout << path[i][j] << " ";
    cout << endl;
  }*/

  
  for(int index=0 ; index<(int)table.size() ; index++){
    //先選出當前table最小的ID是誰
    int shortest = maxint,ID = -1;
    for(int i=0 ; i<(int)table.size() ; i++){
      //vector<int> closed的作法
      /*for(int j=0 ; j<(int)closed.size() ; j++){
        if(i == closed[j]){
          idt = 0;
          j = closed.size();
        }
      }*/
      if(!closed[i]){
          if(table[i] < shortest){
            shortest = table[i];
            ID = i;
          }
      }    
    }
    closed[ID] = 1;
    //若選出的ID與目的地相同，則跳出迴圈
    if(ID == dest)
      break;

    //從上面選出來的點(ID)去探能否鬆弛(置換較小的距離)
    for(int i=0 ; i<(int)table.size(); i++){
      //vector<int> closed的作法
      /*for(int j=0 ; j<(int)closed.size() ; j++){
        if(i == closed[j]){
          idt = 0;
          j = closed.size();
        }
      }*/
      if(!closed[i]){//從(選擇的)下個點開始去看該點的鄰居
        if(table[ID] + graph[ID][i] < table[i]){//看鄰居是否需要置換
          table[i] = table[ID] + graph[ID][i];
          prev[i] = ID;
          //若有鬆弛，則將path重整
          /*for(int tmp=path[i].size()-1 ; tmp>=1 ; tmp--)
            path[i].pop_back();*/

          //從index = 1開始去補充前面ID的path
          /*for(int tmp=1; tmp<(int)path[ID].size(); tmp++)
            path[i].push_back(path[ID][tmp]);
          path[i].push_back(i);*/
        }
      }
    }

  //while(1)的時候，break的判斷
    /*int times = 0;
    for(int i=0 ; i<(int)table.size() ; i++){
        if(closed[i] == 1)
          times++;
    }
    if(times == (int)table.size())
      break;*/
  }


  int idx = dest;int num = 0;
  int Path[(int)table.size()];

  while(prev[idx] != -1){   
    Path[num++] = idx;
    idx = prev[idx];
  }

  return Path[num-1];

  //return path[dest][1];

//將最後path印出來偵錯
/*
cout << "{ " << start << " " << dest << endl;
  for(int i=0 ;i<table.size(); i++){
    cout << i << ": ";
    for(int j=0 ; j<path[i].size(); j++){
      cout << path[i][j] << " ";
    }
    cout << endl;
  }
  cout << "\n}\n";*/
}

/*
5 2 8
1 4
0 0 1 1 3
1 0 2 1 3
2 0 3 3 1
3 1 2 1 3
4 1 3 1 1
5 2 3 1 1
6 2 4 3 1
7 3 4 1 3
*/