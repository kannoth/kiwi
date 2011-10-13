#pragma once
#ifndef KIWI_CORE_DATASTRATEGY_HPP
#define KIWI_CORE_DATASTRATEGY_HPP

namespace kiwi{
namespace core{

class DataTypeInfo;
class Data;


class DataStrategy
{
public:
    virtual const DataTypeInfo* dataType() const = 0;
    virtual Data* data() = 0;
    virtual const Data* data() const = 0;
    virtual ~DataStrategy(){}
};

class AutoDataStrategy : public DataStrategy
{
public:
    AutoDataStrategy(const DataTypeInfo* info)
    : _dataTypeInfo(info)
    {

    }
    
    virtual const DataTypeInfo* dataType() const
    {
        return _dataTypeInfo;
    }
    
    virtual Data* data()
    {
        return _data;
    }

    virtual const Data* data() const
    {
        return _data;
    }
    
private:
    const DataTypeInfo* _dataTypeInfo; 
    Data* _data; 
};


} //namespace
} //namespace


#endif
