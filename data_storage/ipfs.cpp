#include <ipfs/api/ipfs_api.hpp>
#include <ipfs/impl/files.hpp>

class IpfsDataStorage {
public:
    IpfsDataStorage(std::string nodeUrl) : nodeUrl(nodeUrl) {
        // Initialize the IPFS node with the given URL
    }

    void addFile(std::string filePath) {
        // Add a file to the IPFS node
        ipfs::api::IpfsApi api(nodeUrl);
        api.AddFile(filePath);
    }

    void getFile(std::string cid) {
        // Get a file from the IPFS node by its CID
        ipfs::api::IpfsApi api(nodeUrl);
        api.GetFile(cid);
    }

private:
    std::string nodeUrl;
};
