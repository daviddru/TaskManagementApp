//
// Created by David Druja on 01.06.2025.
//

#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include "Task.h"

class Specification {
public:
    virtual ~Specification() = default;
    virtual bool isSatisfiedBy(const Task& task) const = 0;
};


class DescriptionContainsSpecification : public Specification {
private:
    QString keyword;

public:
    explicit DescriptionContainsSpecification(const QString& keyword): keyword(keyword) {}

    bool isSatisfiedBy(const Task& task) const override {
        return task.getDescription().contains(keyword, Qt::CaseInsensitive);
    }
};


class CompletionSpecification : public Specification {
private:
    bool completed;

public:
    explicit CompletionSpecification(bool completed) : completed(completed) {}

    bool isSatisfiedBy(const Task& task) const override {
        return task.getCompleted() == completed;
    }
};


class AndSpecification : public Specification {
private:
    const Specification& spec1;
    const Specification& spec2;

public:
    AndSpecification(const Specification& s1, const Specification& s2)
        : spec1(s1), spec2(s2) {}

    bool isSatisfiedBy(const Task& task) const override {
        return spec1.isSatisfiedBy(task) && spec2.isSatisfiedBy(task);
    }
};


class OrSpecification : public Specification {
private:
    const Specification& spec1;
    const Specification& spec2;

public:
    OrSpecification(const Specification& s1, const Specification& s2)
        : spec1(s1), spec2(s2) {}

    bool isSatisfiedBy(const Task& task) const override {
        return spec1.isSatisfiedBy(task) || spec2.isSatisfiedBy(task);
    }
};


#endif //SPECIFICATION_H
