# Notes du commit
1) Renomage du fichier note
2) Suppression des notes précédentes
3) passage des méthodes
   void add_card_into_hand(std::unique_ptr<Card>  card_);
   std::unique_ptr<Card>  remove_card_from_hand(int card_index);
   en private
4) Passage du constructeur
   Player::Player(int id_, Player* p, int max_card) : id(id_), player(p), hand{}, max_cards(max_card), claimed_borders{} {}
   à
   Player::Player(int id_) : id(id_), player(this), hand{}, max_cards(6), claimed_borders{} {}
5) passage du constructeur en explicit
6) Création de la méthode std::ostream& operator<<(std::ostream& f, const Player& player);