
#include <iostream>
#include<string>
#include<vector>
using namespace std;


//nous avons fais uniquement l'exercise 1 vue la tres grannde quantite de travail a faire cette semaine , justement on ne voulais pas passer
//cette semaine sans s'entrainer donc on a fait l'exercise 1 on fera l'exercise 2 pour la prochaine fois si vous voulez


class TextPost {
 protected :
    string authorName;
    string message;
    int likes;

public :

    TextPost(const string & authorName, const string & message): 
        authorName(authorName),message(message)
    {
        likes = 0;
    }
    void like() { ++likes; }

    ostream& toOstream(ostream& out) const;
    

};

class Person {
protected:
    string name;
    vector<Person*>friends;
    vector<TextPost>posts;
    bool likesPosts;

public:
    Person(const string& name, const bool& likesPosts=false) :
        name(name),likesPosts(likesPosts)
    {}
    bool getLikesPosts(const Person& p) { return likesPosts; }
    void setLikesPosts(const bool& likesPosts) { this->likesPosts = likesPosts; }

    void addFriend(Person& p) {
        Person* added_friend;
        added_friend = &p;
        friends.push_back(added_friend);
        (p.friends).push_back(this);    
    }
    void receivePost(TextPost& post) const {
        if (likesPosts == true) {
            post.like();
        }
    }

    void post(const string& message){
        TextPost my_post(this->name,message);
        posts.push_back(my_post);
        for (size_t i = 0; i < friends.size(); ++i) {
            friends[i]->receivePost(posts[posts.size()-1]);
        }
        
    }
    ostream& toOstream(ostream& out) const;
 
};

ostream& operator<<(ostream& out, const TextPost& t) { return t.toOstream(out); }
ostream& operator<<(ostream& out, const Person& p) { return p.toOstream(out); }
ostream& TextPost::toOstream(ostream& out) const
{
    out << authorName <<" posted:" << endl << message << endl << "Likes: "<<likes;
    return out;
}

ostream& Person::toOstream(ostream& out) const {
    out << name << " : " << endl << "==========" << endl;
    for (size_t i = 0; i < friends.size(); ++i) {
        out << name << " is friends with  " << friends[i]->name << endl;
    }
    for (size_t i = 0; i < posts.size(); ++i) {
      out << posts[i] << endl;
    }
    return out;
}

int main()
{
    Person peter("Peter");
    Person paul("Paul", true); 
    peter.addFriend(paul);
    // Posts
    peter.post("Peter's first post");
    paul.post("Paul's first post");
    // Use of setters
    peter.setLikesPosts(true);
    // Posts again
    peter.post("Peter's second post");
    paul.post("Paul's second post");
    // Display
    cout<< peter << endl;
    cout<< paul << endl;
    return 0;
}