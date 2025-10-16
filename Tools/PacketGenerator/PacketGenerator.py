import argparse
import jinja2
import ProtoParser

def main():
    
    arg_parser = argparse.ArgumentParser(description = 'PacketGenerator')
    arg_parser.add_argument('--path', type=str, default='C:/Users/User/Documents/GitHub/FishingServer/MainServer/vcpkg_installed/x64-windows/x64-windows/tools/protobuf/Protocol.proto', help='proto path')    
    arg_parser.add_argument('--output', type=str, default='TestPacketHandler', help='output file')    
    arg_parser.add_argument('--recv', type=str, default='REQ_', help='recv convention')    
    arg_parser.add_argument('--send', type=str, default='RES_', help='send convention')
    arg_parser.add_argument('--notify', type=str, default='NOTIFY_', help='notify convention')
    args = arg_parser.parse_args()
    
    parser = ProtoParser.ProtoParser(1000, args.recv, args.send, args.notify)
    parser.parse_proto(args.path)

    file_loader = jinja2.FileSystemLoader('Templates')
    env = jinja2.Environment(loader=file_loader, auto_reload=True,cache_size=0)
    
    template = env.get_template('PacketHandler.h')
    output = template.render(parser=parser, output=args.output)
    
    f = open(args.output+'.h', 'w+')
    f.write(output)
    f.close()
    
    print(output)
    return

if __name__ == "__main__":
    main()