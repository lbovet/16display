from pythonosc import udp_client
Import("env")

client = udp_client.SimpleUDPClient("127.0.0.1", 6101)

def before_upload(source, target, env):
    print("Disconnecting 16box")
    client.send_message("/connect", 0)


def after_upload(source, target, env):
    print("Connecting 16box")
    client.send_message("/connect", 1)

env.AddPreAction("upload", before_upload)
env.AddPostAction("upload", after_upload)
