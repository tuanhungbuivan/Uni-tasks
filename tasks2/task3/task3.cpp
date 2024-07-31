#include <vector>
#include <cstdint>
#include <iostream>
#include <cstddef>
#include <bitset>

using namespace std;

class BitStream {
public:
     vector<char> data_;
     uint32_t bitsOccupied_ = 0;

     uint32_t calculateRequiredAdditionalBytes(uint32_t const bits)
     {
          auto wholeBytes = bits / 8;
          if (bits % 8 != 0) wholeBytes++;
          return wholeBytes;
     }

     void ensureSufficientCapacity(uint32_t const bitLength)
     {
          auto const availableBits = data_.size() * 8 - bitsOccupied_;

          if (availableBits < bitLength) {
               auto const requiredAdditionalBits = bitLength - availableBits;
               auto const requiredAdditionalBytes =
                         calculateRequiredAdditionalBytes(requiredAdditionalBits);
               data_.insert(data_.end(), requiredAdditionalBytes, char(0));
          }
     }

     class BitIterator {
          char* source_;
          unsigned int bit : 3;

     public:
          BitIterator(char* source, uint32_t byteOffset, uint32_t bitOffset)
               : source_(source + byteOffset), bit(bitOffset) { }

          BitIterator& operator++() {
               if (bit == 7) ++source_;
               ++bit;
               return *this;
          }

          void assign_bit_from(BitIterator const other){
               uint32_t const isOtherBitSet = (*(other.source_) & char(1 << other.bit)) == char(0);

               if (isOtherBitSet) {
                    *source_ |= char(1 << bit);
               } else {
                    *source_ &= ~char(1 << bit);
               }
          }
/*
          BitIterator& operator--() {
               if (bit == 0) --source_;
               bit--;
               return *this;
          }

          uint32_t get_bit_to(BitIterator const other){
               uint32_t bits = ((*other.source_) & ~(~0 << 1)) == char(0);

               *source_ >> 1;

               return bits;
          }
*/
};

public:

     uint32_t Add(uint32_t const bitLength, void* dataAddr)
     {
          ensureSufficientCapacity(bitLength);

          uint32_t byteIndex = bitsOccupied_ / 8;
          uint32_t bitIndex = bitsOccupied_ % 8;

          auto streamIterator = BitIterator(data_.data(), byteIndex, bitIndex);
          auto dataIterator = BitIterator(static_cast<char*>(dataAddr), 0, 0);

          for (uint32_t i = uint32_t(0); i < bitLength; i++) {
               streamIterator.assign_bit_from(dataIterator);
               ++streamIterator;
               ++dataIterator;
          }

          bitsOccupied_ += bitLength;

          return bitsOccupied_;
     }
     /*
     uint32_t Get(uint32_t const bitLength, void* dataAddr)
     {

          uint32_t byteIndex = bitsOccupied_ / 8;
          uint32_t bitIndex = bitsOccupied_ % 8;

          auto streamIterator = BitIterator(data_.data(), byteIndex, bitIndex);
          auto dataIterator = BitIterator(static_cast<char*>(dataAddr), 0, 0);

          for (uint32_t i = uint32_t(0); i < bitLength; i++) {
               streamIterator.get_bit_to(dataIterator);
               ++streamIterator;
               ++dataIterator;
          }

          bitsOccupied_ -=bitLength;

          return bitsOccupied_;
     }
     
     uint32_t GetBitLength()
     {
          return bitsOccupied_;
     }

     BitStream GetData(void* addr, uint32_t maxBitLength)
     {


     }

     BitStream Reset()
     {
          auto streamIterator = BitIterator(data_.data(), byteIndex, bitIndex);
          for (uint32_t i = uint32_t(0); i < bitsOccupied; i++) {
               streamIterator.reset();
          }
          vector<char> to_reset = data_;

          delete data_;
     }*/



};

//char* temp = (char*)*source_;
int main()
{
     auto stream = BitStream();
     auto x = 2;

     stream.Add(2, &x);
     stream.Add(2, &x);
     stream.Add(4, &x);
     stream.Add(2, &x);

     cout << stream.data_.size() << '\n';
     cout << bitset<8>(static_cast<uint8_t>(stream.data_[0]));

}
