
class TApplication
{
	class Polynom *polynom;
	bool isActive = true;
	
public:
	TApplication();
	~TApplication();
	
	int exec();
	
private:
	void menu();
};
