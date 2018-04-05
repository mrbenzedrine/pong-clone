class Score
{
    public:
        void incrementScore(){scoreValue++;};
        int getScore() const {return scoreValue;};

    private:
        int scoreValue;

};
