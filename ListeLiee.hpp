#pragma once
#include "gsl/gsl_assert"
#include "gsl/pointers"

template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
class Noeud
{
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
public:
	Noeud(const T& donnee, Noeud<T>* suivant = nullptr, Noeud<T>* precedent = nullptr)
		: donnee_(donnee), suivant_(suivant), precedent_(precedent) {}
private:
	T donnee_;
	Noeud<T>* suivant_;
	Noeud<T>* precedent_;
};

template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	Iterateur(Noeud<T>* position) : position_(position) {}

	void avancer()
	{
		Expects(position_ != nullptr);
		position_ = position_->suivant_;
	}

	void reculer()
	{
		Expects(position_ != nullptr);
		position_ = position_->precedent_;
	}

	T& operator*()
	{
		return position_->donnee_;
	}

	Iterateur<T>& operator++()
	{
		avancer();
		return *this;
	}

	Iterateur<T> operator++(int)
	{
		Iterateur<T> temp = *this;
		avancer();
		return temp;
	}

	bool operator!=(const Iterateur<T>& it) const
	{
		return position_ != it.position_;
	}

	bool operator==(const Iterateur<T>& it) const = default;
private:
	Noeud<T>* position_;
};

template<typename T>
class ListeLiee
{
	friend class Iterateur<T>;
public:
	using iterator = Iterateur<T>;

	ListeLiee() : tete_(nullptr), queue_(nullptr), taille_(0) {}

	~ListeLiee()
	{
		while (tete_ != nullptr)
		{
			Noeud<T>* temp = tete_;
			tete_ = tete_->suivant_;
			delete temp;
		}
	}

	bool estVide() const { return taille_ == 0; }
	unsigned size() const { return taille_; }

	iterator begin() { return { tete_ }; }
	iterator end() { return { nullptr }; }

	void push_back(const T& item)
	{
		Noeud<T>* nouveauNoeud = new Noeud<T>(item);
		if (estVide())
		{
			tete_ = queue_ = nouveauNoeud;
		}

		else
		{
			queue_->suivant_ = nouveauNoeud;
			nouveauNoeud->precedent_ = queue_;
			queue_ = nouveauNoeud;
		}
		taille_++;
	}

	iterator insert(iterator it, const T& item)
	{
		Noeud<T>* position = it.position_;
		Noeud<T>* nouveauNoeud = new Noeud<T>(item);

		if (position->precedent_ != nullptr)
		{
			position->precedent_->suivant_ = nouveauNoeud;
			nouveauNoeud->precedent_ = position->precedent_;
		}

		else 
		{
			tete_ = nouveauNoeud;
		}

		nouveauNoeud->suivant_ = position;
		position->precedent_ = nouveauNoeud;

		taille_++;
		return iterator(nouveauNoeud);
	}

	iterator erase(iterator it)
	{
		Noeud<T>* position = it.position_;
		if (position == tete_) 
		{
			tete_ = position->suivant_;
			if (tete_ != nullptr) 
			{
				tete_->precedent_ = nullptr;
			}
		}
		else 
		{
			position->precedent_->suivant_ = position->suivant_;
		}

		if (position->suivant_ != nullptr)
		{
			position->suivant_->precedent_ = position->precedent_;
		}

		Noeud<T>* suivant = position->suivant_;
		delete position;
		taille_--;
		return iterator(suivant);
	}

private:
	gsl::owner<Noeud<T>*> tete_;
	Noeud<T>* queue_;
	unsigned taille_;
};
